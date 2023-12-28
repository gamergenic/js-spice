const expect = require('chai').expect;
const { spice } = require('..');

describe('psv2pl', function() {
  it('should make a SPICE plane from a point and two spanning vectors.', function() {
    const point = [1, 2, 3];
    const span1 = [1, 1, 0];
    const span2 = [0, 1, 1];
    
    const actual = spice.psv2pl(point, span1, span2);

    // "expect" the vector to be normalized
    const expected = {
        "normal": [0.5773502691896258,-0.5773502691896258,0.5773502691896258],
        "constant": 1.154700538379252
    };

    expect(actual).to.deep.equal(expected);
  });
});
