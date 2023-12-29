const expect = require('chai').expect;

/**
 * Custom assertion function to check if two objects or arrays are almost equal, allowing for a specified tolerance.
 * The function compares each numerical value within the objects/arrays and asserts that they are close within the given tolerance.
 * For non-numerical values, a deep equality check is performed.
 *
 * @param {Object|Array} actual - The actual object/array to be tested.
 * @param {Object|Array} expected - The expected object/array to compare against.
 * @param {number} tolerance - The tolerance within which numerical values are considered equal.
 */
function expectAlmostEqual(actual, expected, tolerance) {
    // Assert that both objects have the same keys
    expect(actual).to.have.keys(Object.keys(expected));

    for (const key in expected) {
        if (typeof expected[key] === 'number') {
            // For numerical values, check if they are close within the tolerance
            expect(actual[key]).to.be.closeTo(expected[key], tolerance);
        } else if (Array.isArray(expected[key])) {
            // For arrays, check length and compare each element
            expect(actual[key]).to.be.an('array').with.lengthOf(expected[key].length);
            for (let i = 0; i < expected[key].length; i++) {
                expect(actual[key][i]).to.be.closeTo(expected[key][i], tolerance);
            }
        } else {
            // For other types, check for deep equality
            expect(actual[key]).to.deep.equal(expected[key]);
        }
    }
}

// Export the function for use in tests
module.exports = expectAlmostEqual;
