const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./expectAlmostEqual');

describe('vlcom3', function() {
  it('should compute the vector linear combination of three double precision 3-dimensional vectors.', function() {
    const a = 1;
    const v1 = [1, 2, 3];
    const b = 2;
    const v2 = [4, 5, 6];
    const c = 3;
    const v3 = [7, 8, 9];

    let actual = spice.vlcom3(a, v1, b, v2, c, v3);

    let expected = [1*1+2*4+3*7, 1*2+2*5+3*8, 1*3+2*6+3*9];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);      
  });

  it('should throw an error if invoked with a missing arg', function() {
    function test(){
        const a = 1;
        const v1 = [1, 2, 3];
        const b = 2;
        const v2 = [4, 5, 6];
        const c = 3;
    
        spice.vlcom3(a, v1, b, v2, c);
    }

    expect(test).to.throw();
  });

  it('should throw an error if invoked with an incorrect arg type', function() {
    function test(){
        const a = 1;
        const v1 = [1, 2, 3];
        const b = 2;
        const v2 = [4, 5, 6];
        const c = true;
        const v3 = [7, 8, 9];
    
        spice.vlcom3(a, v1, b, v2, c, v3);
    }

    expect(test).to.throw();
  });

  
  it('should throw an error if invoked with an extra arg', function() {
    function test(){
        const a = 1;
        const v1 = [1, 2, 3];
        const b = 2;
        const v2 = [4, 5, 6];
        const c = 3;
        const v3 = [7, 8, 9];
    
        spice.vlcom3(a, v1, b, v2, c, v3, false);
    }

    expect(test).to.throw();
  });   
  
});
