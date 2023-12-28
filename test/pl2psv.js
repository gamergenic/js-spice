const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./expectAlmostEqual');

describe('pl2psv', function() {
  it('should return a point and two orthogonal spanning vectors that generate a specified plane.', function() {
    const plane = { normal:[1, 2, 3], constant:4 };
    
    const actual = spice.pl2psv(plane);

    expect(actual).to.be.an('object');
    expect(actual).to.have.all.keys('point', 'span1', 'span2');
    expect(actual.point).to.be.an('array').with.lengthOf(3);
    expect(actual.point[0]).to.be.a('number');
    expect(actual.point[1]).to.be.a('number');
    expect(actual.point[2]).to.be.a('number');       
    expect(actual.span1).to.be.an('array').with.lengthOf(3);
    expect(actual.span1[0]).to.be.a('number');
    expect(actual.span1[1]).to.be.a('number');
    expect(actual.span1[2]).to.be.a('number');       
    expect(actual.span2).to.be.an('array').with.lengthOf(3);
    expect(actual.span2[0]).to.be.a('number');
    expect(actual.span2[1]).to.be.a('number');
    expect(actual.span2[2]).to.be.a('number');

    // there's 4 degrees of freedom but 9 values meaning the actual values
    // of point, span1, span2 need represented differently to evaluate the value.
    // So, lean on spice to convert the "actual" to such a representation.
    // We use psv2pl, which itself is a unit-tested function,
    // double check that point, span1, span2 give us the equivalent of the original
    // plane if psv2pl is used on them.
    const doubleCheck = spice.psv2pl(actual.point, actual.span1, actual.span2);

    const expected = {
        "normal": [0.2672612419124244,0.5345224838248488,0.8017837257372733],
        "constant": 1.0690449676496976
    };

    const tolerance = 1e-10; // Define a suitable tolerance
    expectAlmostEqual(doubleCheck, expected, tolerance);    
  });
});
