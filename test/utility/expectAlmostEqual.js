const expect = require('chai').expect;

function expectAlmostEqual(actual, expected, tolerance) {
    expect(actual).to.have.keys(Object.keys(expected));
    for (const key in expected) {
        if (typeof expected[key] === 'number') {
            expect(actual[key]).to.be.closeTo(expected[key], tolerance);
        } else if (Array.isArray(expected[key])) {
            expect(actual[key]).to.be.an('array').with.lengthOf(expected[key].length);
            for (let i = 0; i < expected[key].length; i++) {
                expect(actual[key][i]).to.be.closeTo(expected[key][i], tolerance);
            }
        } else {
            expect(actual[key]).to.deep.equal(expected[key]);
        }
    }
}

module.exports = expectAlmostEqual;