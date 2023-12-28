const expect = require('chai').expect;
const { spice } = require('..');

describe('vperp', function() {
  it('should pack three scalar components into a vector array [x,y,z].', function() {
    const a = [6, 6, 6];
    const b = [2, 0, 0];
    
    const actual = spice.vperp(a, b);
    
    const expected = [0, 6, 6];
    expect(actual[0]).to.be.closeTo(expected[0], 0.00001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.00001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.00001);
  });

  it('should throw an error if invoked with an extra arg', function() {
    function test(){
        const a = [6, 6, 6];
        const b = [2, 0, 0];
                
        spice.vperp(a, b, null);
    }

    expect(test).to.throw();
  });  
});
