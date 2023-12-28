const expect = require('chai').expect;
const { spice } = require('..');

describe('vpack', function() {
  it('should pack three scalar components into a vector array [x,y,z].', function() {

    let actual = spice.vpack(-1, -2, -3);
    let expected = [-1, -2, -3];

    expect(-1).to.be.closeTo(expected[0], 0.0001);
    expect(-2).to.be.closeTo(expected[1], 0.0001);
    expect(-3).to.be.closeTo(expected[2], 0.0001);
  });

  it('should throw an error if invoked with an extra arg', function() {
    function test(){
        spice.vpack(-1, -2, -3, -4);
    }

    expect(test).to.throw();
  });  
});
