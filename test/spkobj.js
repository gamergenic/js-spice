const expect = require('chai').expect;
const { spice } = require('..');

const { initializeFileAndDirectory, cleanupFileAndDirectory } = require('./utility/fileUtils');

describe('spkobj', function() {
  it('should find the set of ID codes of all objects in a specified SPK file.',
   function() {

        // To test that spkw05 write a segment, we'll:
        // 1 open a new spk for writing
        // 2 write some data
        // 3 close it
        // 4 use spkobj to verify it contains the object we wrote ephemeris data for.
        const testFilePath = './test/temp/test_spkobj.bsp';
        const mu = 1;
        const oscelt = {"rp":1, "ecc":0, "inc":0, "lnode":0, "argp":0, "m0":0, "t0":0, "mu":1};
        var samples = [];

        for(et = 0; et < spice.spd(); et += spice.spd()/24){
            samples.push({"state": spice.conics(oscelt, et), "et": et});
        }

        // make sure the directory exists and the test's target file does not.
        initializeFileAndDirectory(testFilePath); 

        let handle = spice.spkopn(testFilePath, 'test_spkobj', 80);
        
        function spkw05(){
            spice.spkw05(handle, -12345, 399, "J2000", 0, spice.spd(), "blue", mu, samples);
            spice.spkw05(handle, -23456, 399, "J2000", 0, spice.spd(), "fish", mu, samples);
            spice.spkw05(handle, -34567, 399, "J2000", 0, spice.spd(), "swim", mu, samples);
            spice.spkw05(handle, -45678, 399, "J2000", 0, spice.spd(), "near", mu, samples);
            spice.spkw05(handle, -56789, 399, "J2000", 0, spice.spd(), "deep", mu, samples);
            spice.spkw05(handle, -67890, 399, "J2000", 0, spice.spd(), "reef", mu, samples);
        }
        expect(spkw05).to.not.throw();
               
        spice.spkcls(handle);

        const coverage = spice.spkobj(testFilePath);

        cleanupFileAndDirectory(testFilePath); 

        const expectedCoverageList = [-12345, -23456, -34567, -45678, -56789, -67890];
        const sortedCoverageList = coverage.sort((a, b) => b - a);
        expect(sortedCoverageList).to.deep.equal(expectedCoverageList);
    });
});
