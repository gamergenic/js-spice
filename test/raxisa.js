const expect = require('chai').expect;
const { spice } = require('..');

describe('raxisa', function() {
  it('should compute the axis of the rotation given by an input matrix and the angle',
  function() {

    const m = [[0, 1, 0], [-1, 0, 0], [0, 0, 1]];

    const {axis, angle} = spice.raxisa(m);

    expect(axis[0]).to.be.closeTo(0, 1e-6);
    expect(axis[1]).to.be.closeTo(0, 1e-6);
    expect(axis[2]).to.be.closeTo(-1, 1e-6);
    expect(angle).to.be.closeTo(3.14159265358979/2, 1e-6);
  });
});
