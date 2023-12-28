const expect = require('chai').expect;
const { spice } = require('..');

describe('vequ', function() {
  it('Make one double precision 3-dimensional vector equal to another', function() {
    let vin = [1, 2, 3];

    let actual = spice.vequ(vin);

    let expected = [1, 2, 3];

    expect(actual[0]).to.be.closeTo(expected[0], 0.0001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.0001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.0001);
  });

  it('Make one double precision 3-dimensional vector equal to another (object vector)', function() {
    let vin = { "x": 1, "y": 2, "z": 3};

    let actual = spice.vequ(vin);

    let expected = [1, 2, 3];

    expect(actual[0]).to.be.closeTo(expected[0], 0.0001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.0001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.0001);
  });

  it('Make one double precision 3-dimensional vector equal to another (x, y, z as args)', function() {
    let actual = spice.vequ(1, 2, 3);

    let expected = [1, 2, 3];

    expect(actual[0]).to.be.closeTo(expected[0], 0.0001);
    expect(actual[1]).to.be.closeTo(expected[1], 0.0001);
    expect(actual[2]).to.be.closeTo(expected[2], 0.0001);
  });


  it('should throws an error if invoked with no params', function() {
    function test(){
      spice.vequ();
    }

    expect(test).to.throw();
  });
  
  it('should throws an error if invoked with extra params', function() {
    function test(){
      let vin = {"x": 0, "y": 0, "z": 1};
      spice.vequ(vin, vin);
    }

    expect(test).to.throw();
  });   
  
});
