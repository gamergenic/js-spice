const fs = require('fs');
const path = require('path');

function initializeFileAndDirectory(filePath) {
    const directoryPath = path.dirname(filePath);

    try {
        // Create directory if it doesn't exist
        if (!fs.existsSync(directoryPath)) {
            fs.mkdirSync(directoryPath, { recursive: true });
        }

        // Delete file if it exists
        if (fs.existsSync(filePath)) {
            fs.unlinkSync(filePath);
        }
    } catch (err) {
        console.error(`An error occurred: ${err.message}`);
    }
}


function cleanupFileAndDirectory(filePath) {
    try {
        // Delete the file if it exists
        if (fs.existsSync(filePath)) {
            fs.unlinkSync(filePath);
        }

        // Get directory path
        const directoryPath = path.dirname(filePath);

        // Read the contents of the directory
        const files = fs.readdirSync(directoryPath);

        // If the directory is empty, delete it
        if (files.length === 0) {
            fs.rmdirSync(directoryPath);
        }
    } catch (err) {
        console.error(`An error occurred: ${err.message}`);
    }
}

module.exports = { initializeFileAndDirectory, cleanupFileAndDirectory };