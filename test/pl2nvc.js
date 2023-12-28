const expect = require('chai').expect;
const { spice } = require('..');

describe('pl2nvc', function() {
  it('should return a unit normal vector and constant that define a specified plane.', function() {
    const plane = { normal:[1, 2, 3], constant:4 };
    
    const actual = spice.pl2nvc(plane);

    // "expect" the vector to be normalized in the result and the constant adjusted accordingly
    const expected = {
        "normal": [0.2672612419124244,0.5345224838248488,0.8017837257372733],
        "constant": 1.0690449676496976
    };

    expect(actual).to.deep.equal(expected);
  });
});
