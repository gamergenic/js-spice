const expect = require('chai').expect;
const { spice } = require('..');

describe('ident', function() {
  it('should return the 3x3 identity matrix.',
   function() {

    const actual = spice.ident();

    const expected = [[1,0,0], [0,1,0], [0,0,1]];
    
    expect(actual).to.deep.equal(expected); 
  });
});
