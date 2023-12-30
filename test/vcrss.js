const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vcrss', function() {
  it('should compute the cross product of two 3-dimensional vectors.',
   function() {

    const v1 = [0, 1, 0];
    const v2 = [1, 0, 0];
    
    const actual = spice.vcrss(v1, v2);

    const expected = [0, 0, -1];
    const tolerance = 1e-5;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
