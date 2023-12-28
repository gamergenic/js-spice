const expect = require('chai').expect;
const { spice } = require('..');

describe('axisar', function() {
  it('should construct a rotation matrix that rotates vectors by a specified \
angle about a specified axis.', function() {
    let axis = [0,0,1];
    let angle = 3.1415926536;

    let actual = spice.axisar(axis, angle);

    let expected = [[-1,0,0],[0,-1,0],[0,0,1]];
    for (let i = 0; i < actual.length; i++) {
      for (let j = 0; j < actual[i].length; j++) {
        expect(actual[i][j]).to.be.closeTo(expected[i][j], 0.0001);
      }
    }
  });

  it('should accept axis as {x:,y:,z:} object', function() {
    let axis = {"x": 0, "y": 0, "z": 1};
    let angle = 3.1415926536;

    let actual = spice.axisar(axis, angle);

    let expected = [[-1,0,0],[0,-1,0],[0,0,1]];
    for (let i = 0; i < actual.length; i++) {
      for (let j = 0; j < actual[i].length; j++) {
        expect(actual[i][j]).to.be.closeTo(expected[i][j], 0.0001);
      }
    }
  });
  
  it('should accept axis as (x, y, z) args', function() {
    let actual = spice.axisar(0, 0, 1, 3.14159);

    let expected = [[-1,0,0],[0,-1,0],[0,0,1]];
    for (let i = 0; i < actual.length; i++) {
      for (let j = 0; j < actual[i].length; j++) {
        expect(actual[i][j]).to.be.closeTo(expected[i][j], 0.0001);
      }
    }
  });
  
  it('should throws an error in invoked with no arg', function() {
    function test(){
      spice.axisar();
    }

    expect(test).to.throw();
  });
  
  it('should throws an error if invoked with extra args', function() {
    function test(){
      let axis = {"x": 0, "y": 0, "z": 1};
      let angle = 3.14159;

      spice.axisar(axis, angle, 0);
    }

    expect(test).to.throw();
  });   
});
