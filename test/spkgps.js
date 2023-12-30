const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('spkgps', function() {

    // Allow extra time as this is a computationally expensive operation.
    // Plus, we may need to download a number of kernels to run the test.
    this.timeout(60000);

    it('Return compute the geometric position of a target body relative to an \
    observing body.',
    
    async function() {

        const kernelsToLoad = [
            'lsk/a_old_versions/naif0009.tls',
            'pck/a_old_versions/pck00008.tpc',
            'spk/planets/a_old_versions/de421.bsp',
        ];
    
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');   
    
        const {pos, lt} = spice.spkgps(199, spice.str2et("2023 DEC 30"), "J2000", 399);

        const expectedPosition = [-14176382.802773606,-103194287.6067884,-38149177.5006784];
        const expectedLt = 370.0215332284177;

        const tolerance = 1e-6;
        expectAlmostEqual(pos, expectedPosition, tolerance);
        expect(lt).to.be.closeTo(expectedLt, tolerance);
    });
});
