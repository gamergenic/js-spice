const expect = require('chai').expect;
const { spice } = require('..');

describe('sigerr', function() {
    it('should cause a spice error', function() {
        
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
