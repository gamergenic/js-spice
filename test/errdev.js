const expect = require('chai').expect;
const { spice } = require('..');

describe('errdev', function() {
  it('should retrieve or set the name of the current output \
device for error messages.',
   function() {

    const initialValue = spice.errdev('GET');

    const deviceValues = ["./test/temp/tempfile", "SCREEN",  "NULL"];

    deviceValues.map(device => {
        spice.errdev('SET', device);
        expect(spice.errdev('GET')).to.be.equal(device); 
    });

    spice.errdev('SET', initialValue);
  });
});
