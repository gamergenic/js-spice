const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vadd', function() {
  it('should add two double precision 3-dimensional vectors.',
   function() {

    const v1 = [1, 2, 3];
    const v2 = [1, 1, 1];
    
    const actual = spice.vadd(v1, v2);

    const expected = [2, 3, 4];
    const tolerance = 1e-5;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
