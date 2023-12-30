const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('xpose', function() {
  it('should transpose a 3x3 matrix.',
   function() {
    const m =  [[0,  -1,  0],
                [0.5, 0,  0],
                [0,   0,  1] ];

    const actual = spice.xpose(m);

    const expected = [  [ 0,  0.5, 0],
                        [-1,  0,   0],
                        [ 0,  0,   1] ];
    
    const tolerance = 1e-8;
    expectAlmostEqual(actual, expected, tolerance);
  });
});
