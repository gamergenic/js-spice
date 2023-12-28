// test/test.js
const expect = require('chai').expect;
const { spice } = require('..'); // Adjust the path based on your project structure

describe('axisar', function() {
  it('should accept vec3 as array', function() {
    let axis = [0,0,1];
    let angle = 3.14159;

    let actual = spice.axisar(axis, angle);

    let expected = [[-1,0,0],[0,-1,0],[0,0,1]];
    for (let i = 0; i < actual.length; i++) {
      for (let j = 0; j < actual[i].length; j++) {
        expect(actual[i][j]).to.be.closeTo(expected[i][j], 0.0001);
      }
    }
  });

  it('should accept vec3 as {x:,y:,z:} object', function() {
    let axis = {"x": 0, "y": 0, "z": 1};
    let angle = 3.14159;

    let actual = spice.axisar(axis, angle);

    let expected = [[-1,0,0],[0,-1,0],[0,0,1]];
    for (let i = 0; i < actual.length; i++) {
      for (let j = 0; j < actual[i].length; j++) {
        expect(actual[i][j]).to.be.closeTo(expected[i][j], 0.0001);
      }
    }
  });
  
  it('should accept vec3 as (x, y, z) args', function() {
    let actual = spice.axisar(0, 0, 1, 3.14159);

    let expected = [[-1,0,0],[0,-1,0],[0,0,1]];
    for (let i = 0; i < actual.length; i++) {
      for (let j = 0; j < actual[i].length; j++) {
        expect(actual[i][j]).to.be.closeTo(expected[i][j], 0.0001);
      }
    }
  });
  
  it('should throws an error with no params', function() {
    function test(){
      spice.axisar();
    }

    expect(test).to.throw();
  });
  
  it('should throws an error with extra params', function() {
    function test(){
      let axis = {"x": 0, "y": 0, "z": 1};
      let angle = 3.14159;

      spice.axisar(axis, angle, 0);
    }

    expect(test).to.throw();
  });   
});
