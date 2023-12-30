const expect = require('chai').expect;
const { spice } = require('..');

describe('erract', function() {
  it('should retrieve or set the default error action.',
   function() {

    const initialValue = spice.erract('GET');

    const actionValues = ["ABORT",  "IGNORE", "REPORT", "RETURN", "DEFAULT"];

    actionValues.map(action => {
        spice.erract('SET', action);
        expect(spice.erract('GET')).to.be.equal(action); 
    });

    spice.erract('SET', initialValue);
  });
});
