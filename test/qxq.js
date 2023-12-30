const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('qxq', function() {
  it('should multiply two quaternions',
   function() {
    
    const q1 = {"x":1, "y":0, "z":0, "w":0};
    const q2 = {"x":0, "y":1, "z":0, "w":0};

    const actual = spice.qxq(q1, q2);

    const expected = {"x":0, "y":0, "z":1, "w":0};

    const tolerance = 1e-8;
    expectAlmostEqual(actual, expected, tolerance);
  });
});
