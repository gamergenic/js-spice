const expect = require('chai').expect;
const { spice } = require('..');

describe('convrt', function() {
  it('should convert Units (300 miles to kilometers)', function() {

    const distsm = 300.0;
    const actual = spice.convrt(distsm, "statute_miles", "km");
    
    const expected = 482.803200;
    expect(actual).to.be.equal(expected);
  });

  it('should convert 1 parsec to 3.261564 lightyears)', function() {

    const onpars = 1.0;
    const actual = spice.convrt(onpars, "PARSECS", "LIGHTYEARS");
    
    const expected = 3.261564;
    expect(actual).to.be.closeTo(expected, 1e-5);
  });
  
  it('should throw an error converting days to yards', function() {
    function test(){
        spice.convrt(1, "days", "yards");
    }

    expect(test).to.throw();
  });

  it('should throw an error converting light-years to beard-seconds', function() {
    function test(){
        spice.convrt(1, "lightyears", "beardseconds");
    }

    expect(test).to.throw();
  });
});
