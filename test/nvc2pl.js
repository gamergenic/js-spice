const expect = require('chai').expect;
const { spice } = require('..');

describe('nvc2pl', function() {
  it('should make a SPICE plane from a normal vector and a constant.', function() {
    const normal = [1, 2, 3];
    const constant = 4;
    
    const actual = spice.nvc2pl(normal, constant);

    // "expect" the vector to be normalized in the result and the constant adjusted accordingly
    const expected = {
        "normal": [0.2672612419124244,0.5345224838248488,0.8017837257372733],
        "constant": 1.0690449676496976
    };

    expect(actual).to.deep.equal(expected);
  });
});
