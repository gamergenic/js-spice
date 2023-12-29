const expect = require('chai').expect;
const { spice } = require('..');

describe('failed', function() {
    it('should return false if no error is currently signaled', function() {
        // clear any errors
        spice.reset();
        
        // get the error status
        const failed = spice.failed();
        
        // validation
        expect(failed).to.be.equal(false);
    });
    
    it('should return true if an error is currently signaled', function() {
        
        // signal an error
        spice.sigerr('houston, we have a problem.');
        
        // get the error status
        const failed = spice.failed();
        
        // failure is not an option.
        spice.reset();

        // validation
        expect(failed).to.be.equal(true);
    });     
});            
