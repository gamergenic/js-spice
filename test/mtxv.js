const expect = require('chai').expect;
const { spice } = require('..');

describe('mtxv', function() {
  it('matrix transpose times unit x-vector should equal matrix top row', function() {
    let m = [[1, 2, 3], [4,5,6], [7,8,9]];
    let v = [1, 0, 0];

    let actual = spice.mtxv(m, v);

    let expected = [1, 2, 3];

    expect(actual[0]).to.be.closeTo(expected[0], 0.0001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.0001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.0001);
  });
});
