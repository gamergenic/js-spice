const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('vhat', function() {
  it('should find the unit vector along a double precision 3-dimensional vector.', function() {

    let v1 = [5.0,  12.0,  0.0];
    let actual = spice.vhat(v1);
    let expected = [0.38461538, 0.92307692, 0.00000000];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);      
  });

  it('should find the unit vector along a double precision 3-dimensional vector of small numbers.', function() {

    let v1 = [1e-7,  2e-7, 2e-7];
    let actual = spice.vhat(v1);
    let expected = [0.33333333,  0.66666667,  0.66666667];

    const tolerance = 1e-5; // Define a suitable tolerance
    expectAlmostEqual(actual, expected, tolerance);      
  });

  it('should throw an error if invoked with a null arg', function() {
    function test(){
        spice.vhat(null);
    }

    expect(test).to.throw();
  });
  
  it('should throw an error if invoked with no arg', function() {
    function test(){
        spice.vhat();
    }

    expect(test).to.throw();
  });
  
  it('should throw an error if invoked with two args', function() {
    function test(){
        let v1 = [1, 2, 3];
        spice.vhat(v1, v1);
    }

    expect(test).to.throw();
  });

  it('should throw an error if invoked with a 2D vector', function() {
    function test(){
        let v1 = [1, 2];
        spice.vhat(v1, v1);
    }

    expect(test).to.throw();
  });   

  it('should throw an error if invoked with a 4D vector', function() {
    function test(){
        let v1 = [1, 2, 3, 4];
        spice.vhat(v1, v1);
    }

    expect(test).to.throw();
  });   
});
