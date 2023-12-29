const expect = require('chai').expect;
const { spice } = require('..');

describe('reset', function() {
    it('should clear a spice error', function() {
        
        // signal an error
        spice.sigerr('houston, we have a problem.');
        
        // get the error status and verify the error state
        let failed = spice.failed();
        expect(failed).to.be.equal(true);
        
        // failure is not an option.
        spice.reset();

        // validation
        failed = spice.failed();
        expect(failed).to.be.equal(false);
    });     
});            
