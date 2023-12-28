const expect = require('chai').expect;
const { spice } = require('..');

describe('vlcom', function() {
  it('should compute a vector linear combination of two double precision, 3-dimensional vectors.',
  function() {
    const a = 1;
    const v1 = [1, 2, 3];
    const b = 2;
    const v2 = [4, 5, 6];

    let actual = spice.vlcom(a, v1, b, v2);

    let expected = [1*1+2*4, 1*2+2*5, 1*3+2*6];

    expect(actual[0]).to.be.closeTo(expected[0], 0.00001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.00001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.00001);
  });

  it('should throw an error if invoked with a missing arg', function() {
    function test(){
        const a = 1;
        const v1 = [1, 2, 3];
        const b = 2;
    
        spice.vlcom(a, v1, b);
    }

    expect(test).to.throw();
  });

  it('should throw an error if invoked with an incorrect arg type', function() {
    function test(){
        const a = 1;
        const v1 = [1, 2, 3];
        const b = true;
        const v2 = [4, 5, 6];
    
        spice.vlcom(a, v1, b, v2);
    }

    expect(test).to.throw();
  });

  it('should throw an error if invoked with an extra arg', function() {
    function test(){
        const a = 1;
        const v1 = [1, 2, 3];
        const b = 2;
        const v2 = [4, 5, 6];
    
        spice.vlcom(a, v1, b, v2, false);
    }

    expect(test).to.throw();
  });   
});
