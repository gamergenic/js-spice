const axios = require('axios');
const fs = require('fs'); // Use the original fs module
const fsPromises = fs.promises; // For promise-based fs operations
const path = require('path');
const stream = require('stream');
const { promisify } = require('util');
const pipeline = promisify(stream.pipeline);

/**
 * Download a file from a specified URL and save it to a given directory.
 * If the file already exists, the download is skipped. If 'dirRelative' is not
 * provided, the file is saved using 'urlRelative' as a relative path.
 * The function returns the absolute path of the file on the local file system.
 *
 * @param {string} urlRelative The relative URL path from the base URL.
 * @param {string} [dirRelative] Optional. The relative directory path from the base directory.
 * @return {string} The absolute path of the file on the local file system.
 */
async function getGenericKernel(urlRelative, dirRelative) {
  const baseUrl = 'https://naif.jpl.nasa.gov/pub/naif/generic_kernels/';
  const baseDir = './';

  const url = new URL(urlRelative, baseUrl).href;
  const filePath = path.join(baseDir, dirRelative||urlRelative);
  const directory = path.dirname(filePath);
  const resolvedFilePath = path.resolve(filePath);

  try {
    // Check if the file already exists
    try {
      await fsPromises.access(filePath);
      console.log(`File ${resolvedFilePath} already exists, skipping download.`);
      return resolvedFilePath;
    } catch {
      // File does not exist, proceed with download
      console.log('File ${resolvedFilePath} does not exist, starting download.');
    }

    // Ensure the directory exists, creating it if necessary
    await fsPromises.mkdir(directory, { recursive: true });

    const response = await axios({
      method: 'GET',
      url: url,
      responseType: 'stream'
    });

    // Pipe the data stream into a file on disk
    await pipeline(response.data, fs.createWriteStream(filePath));
    console.log('Download and save complete.');

    return resolvedFilePath;
  } catch (error) {
    console.error(`Error downloading the file: ${error.message}`);
    throw error;
  }
}

module.exports = { 
    getGenericKernel
}