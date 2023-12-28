const expect = require('chai').expect;
const { spice } = require('..');

describe('pl2nvp', function() {
  it('should return a unit normal vector and point that define a specified plane.', function() {
    const plane = { normal:[1, 2, 3], constant:4 };
    
    const actual = spice.pl2nvp(plane);

    const expected = {
        "normal": [0.2672612419124244,0.5345224838248488,0.8017837257372733],
        "constant": 1.0690449676496976
    };

    expect(actual).to.be.an('object');
    expect(actual).to.have.all.keys('normal', 'point');
    expect(actual.normal).to.deep.equal(expected.normal);
    expect(actual.point).to.be.an('array').with.lengthOf(3);
    expect(actual.point[0]).to.be.a('number');
    expect(actual.point[1]).to.be.a('number');
    expect(actual.point[2]).to.be.a('number');
    const tolerance = 1e-10; // Define a suitable tolerance
    expect(1 * actual.point[0] + 2 * actual.point[1] + 3 * actual.point[2]).to.be.closeTo(4, tolerance);
  });
});
