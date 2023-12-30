const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('spkgeo', function() {

    // Allow extra time as this is a computationally expensive operation.
    // Plus, we may need to download a number of kernels to run the test.
    this.timeout(60000);

    it('should compute the geometric state (position and velocity) of a target \
body relative to an observing body.',
    
    async function() {

        const kernelsToLoad = [
            'lsk/a_old_versions/naif0009.tls',
            'pck/a_old_versions/pck00008.tpc',
            'spk/planets/a_old_versions/de421.bsp',
        ];
    
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');   
    
        const {state, lt} = spice.spkgeo(199, spice.str2et("2023 DEC 30"), "J2000", 399);

        const expectedState = {
            "r": [-14176382.802773606,-103194287.6067884,-38149177.5006784],
            "v": [-15.351817113026012,-25.72715790054558,-9.421015403049422],
        }
        const expectedLt = 370.0215332284177;

        const tolerance = 1e-6;
        expectAlmostEqual(state, expectedState, tolerance);
        expect(lt).to.be.closeTo(expectedLt, tolerance);
    });
});
