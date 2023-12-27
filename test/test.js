// test/test.js
const expect = require('chai').expect;
const { spice } = require('..'); // Adjust the path based on your project structure

describe('str2et', function() {
  it('should correctly calculate the result', function() {
    let input = 5; // Example input
    let expectedResult = 10; // Replace with the expected result based on your function's logic

    let result = spice.str2et(input);
    expect(result).to.equal(expectedResult);
  });

  // Add more tests as needed
});


describe('furnsh', function() {
    it('should correctly calculate the result', function() {
      let result = spice.furnsh();
    });
  
    // Add more tests as needed
  });

  describe('unload', function() {
    it('should correctly calculate the result', function() {
      let input = 5; // Example input
      let expectedResult = 10; // Replace with the expected result based on your function's logic
  
      let result = spice.unload(input);
      expect(result).to.equal(expectedResult);
    });
  
    // Add more tests as needed
  });