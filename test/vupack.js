const expect = require('chai').expect;
const { spice } = require('..');

describe('vupack', function() {
  it('should unpack three scalar components from a vector.', function() {

    const v = [1, 2, 3];
    const actual = spice.vupack(v);

    const expected = {"x":1, "y":2, "z":3};
    expect(actual).to.deep.equal(expected);      
  });
});
