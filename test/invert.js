const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('invert', function() {
  it('should generate the inverse of a 3x3 matrix.',
   function() {
    const m =  [[0,  -1,  0],
                [0.5, 0,  0],
                [0,   0,  1] ];

    console.log(JSON.stringify(m));

    const actual = spice.invert(m);

    console.log(JSON.stringify(actual));

    const expected = [  [ 0, 2,  0],
                        [-1, 0,  0],
                        [ 0, 0,  1] ];
    
    const tolerance = 1e-8;
    expectAlmostEqual(actual, expected, tolerance);
  });
});
