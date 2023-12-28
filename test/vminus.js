const expect = require('chai').expect;
const { spice } = require('..');

describe('vminus', function() {
  it('should negate a double precision 3-dimensional vector.', function() {

    let v1 = [1, 2, 3];
    let actual = spice.vminus(v1);
    let expected = [-1, -2, -3];

    expect(actual[0]).to.be.closeTo(expected[0], 0.0001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.0001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.0001);
  });

  it('should throw an error if invoked with a null arg', function() {
    function test(){
        spice.vminus(null);
    }

    expect(test).to.throw();
  });  
});
