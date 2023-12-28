const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vrotv', function() {
  it('should rotate a vector about a specified axis vector by a specified \
  angle and return the rotated vector.', function() {

    const v = [1, 2, 3];
    const axis = [0, 0, 1];
    const theta = spice.halfpi();
    
    const actual = spice.vrotv(v, axis, theta);
    
    const expected = [-2,1,3];
    const tolerance = 1e-5;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
