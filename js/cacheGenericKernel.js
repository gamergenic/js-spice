// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

// Required modules
const axios = require('axios');
const fs = require('fs');
const fsPromises = fs.promises;
const path = require('path');
const stream = require('stream');
const { promisify } = require('util');
const pipeline = promisify(stream.pipeline);

/**
 * Asynchronously downloads a file from a specified URL and saves it to a given directory.
 * This function is asynchronous and returns a Promise. It should be used with 'await' in an async function,
 * or with .then()/.catch() for proper handling of the asynchronous operation.
 * If the file already exists, the download is skipped. If 'dirRelative' is not provided,
 * the file is saved using 'urlRelative' as a relative path.
 * The function returns the absolute path of the file on the local file system upon successful download,
 * or if the file already exists.
 *
 * @async
 * @param {string} urlRelative - The relative URL path from the base URL.
 * @param {string} [dirRelative] - Optional. The relative directory path from the base directory.
 * @returns {Promise<string>} - The absolute path of the file on the local file system.
 */

async function cacheGenericKernel(urlRelative, dirRelative) {
  // Base URL and directory for downloads
  const baseUrl = 'https://naif.jpl.nasa.gov/pub/naif/generic_kernels/';
  const baseDir = './';

  // Constructing the full URL and file path
  const url = new URL(urlRelative, baseUrl).href;
  const filePath = path.join(baseDir, dirRelative || urlRelative);
  const directory = path.dirname(filePath);
  const resolvedFilePath = path.resolve(filePath);

  try {
    // Check if the file already exists
    try {
      await fsPromises.access(filePath);
      // Uncomment the below line to log if the file exists
      // console.log(`File ${resolvedFilePath} already exists, skipping download.`);
      return resolvedFilePath;
    } catch {
      // File does not exist, proceed with download
      console.log(`File ${resolvedFilePath} does not exist, starting download.`);
    }

    // Ensure the directory exists, creating it if necessary
    await fsPromises.mkdir(directory, { recursive: true });

    // Initiating the download
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
    // Handling errors during download
    console.error(`Error downloading the file: ${error.message}`);
    throw error;
  }
}

// Exporting the function for external use
module.exports = cacheGenericKernel;
