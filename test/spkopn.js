const expect = require('chai').expect;
const { spice } = require('..');

const { initializeFileAndDirectory, cleanupFileAndDirectory } = require('./utility/fileUtils');

describe('spkopn', function() {
  it('should create a new SPK file.',
   function() {

        // To test that spkopn will create a file, we'll:
        // 1 open a new spk for writing
        // 2 write some data
        // 3 close it
        // ...and expect no exceptions.
        const testFilePath = './test/temp/test_spkopn.bsp';
        const mu = 1;
        const oscelt = {"rp":1, "ecc":0, "inc":0, "lnode":0, "argp":0, "m0":0, "t0":0, "mu":1};
        var samples = [];

        for(et = 0; et < spice.spd(); et += spice.spd()/24){
            samples.push({"state": spice.conics(oscelt, et), "et": et});
        }

        // make sure the directory exists and the test's target file does not.
        initializeFileAndDirectory(testFilePath); 

        let handle = spice.spkopn(testFilePath, 'test_spkopn', 80);
        
        function spkw05(){
            spice.spkw05(handle, -12345, 399, "J2000", 0, spice.spd(), "foo", mu, samples);
        }
        expect(spkw05).to.not.throw();
               
        spice.spkcls(handle);

        cleanupFileAndDirectory(testFilePath); 
    });
});
