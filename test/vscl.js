const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vscl', function() {
  it('should multiply a scalar and a double precision 3-dimensional vector.', function() {

    const s = 2;
    const v1 = [1, 2, 3];
    
    const actual = spice.vscl(s, v1);
    
    const expected = [2,4,6];
    const tolerance = 1e-5;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
