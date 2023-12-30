const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('spkcpt', function() {

    // Allow extra time as this is a computationally expensive operation.
    // Plus, we may need to download a number of kernels to run the test.
    this.timeout(60000);

    it('should return the state, relative to a specified observer, of a target \
having constant position in a specified reference frame.',
    
    async function() {

        // taken from:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/gf.html
        const kernelsToLoad = [
            'lsk/a_old_versions/naif0009.tls',
            'pck/a_old_versions/pck00008.tpc',
            'spk/planets/a_old_versions/de421.bsp',
        ];
    
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');   
    
        const {state, lt} = spice.spkcpt([1,1,1], "mercury", "J2000", spice.str2et("2023 DEC 30"), "J2000", "OBSERVER", "NONE", "EARTH");

        const expectedState = {
            "r": [-14176381.802773606,-103194286.6067884,-38149176.5006784],
            "v": [-15.351817113026012,-25.72715790054558,-9.421015403049422],
        }
        const expectedLt = 370.0215285519557;

        const tolerance = 1e-6;
        expectAlmostEqual(state, expectedState, tolerance);
        expect(lt).to.be.closeTo(expectedLt, tolerance);
    });
});
