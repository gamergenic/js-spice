const expect = require('chai').expect;
const { spice } = require('..');

describe('vlcom3', function() {
  it('compute the vector linear combination of three double precision 3-dimensional vectors.', function() {
    const a = 1;
    const v1 = [1, 2, 3];
    const b = 2;
    const v2 = [4, 5, 6];
    const c = 3;
    const v3 = [7, 8, 9];

    let actual = spice.vlcom3(a, v1, b, v2, c, v3);

    let expected = [1*1+2*4+3*7, 1*2+2*5+3*8, 1*3+2*6+3*9];

    expect(actual[0]).to.be.closeTo(expected[0], 0.0001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.0001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.0001);
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
    
        spice.vlcom3(a, v1, b, v2, c);
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
    
        spice.vlcom3(a, v1, b, v2, c, false);
    }

    expect(test).to.throw();
  });   
  
});
