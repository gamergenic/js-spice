const expect = require('chai').expect;
const { spice } = require('..');

describe('nvp2pl', function() {
  it('should make a SPICE plane from a normal vector and a point.', function() {
    const normal = [1, 2, 3];
    const point = [1, 2, 3];
    
    const actual = spice.nvp2pl(normal, point);

    // "expect" the vector to be normalized
    const expected = {
        "normal": [0.2672612419124244,0.5345224838248488,0.8017837257372733],
        "constant": 3.7416573867739418
    };

    expect(actual).to.deep.equal(expected);
  });
});
