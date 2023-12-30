const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('spkcpo', function() {

    // Allow extra time as this is a computationally expensive operation.
    // Plus, we may need to download a number of kernels to run the test.
    this.timeout(60000);

    it('should return the state of a specified target relative to an "observer", \
    where the observer has constant position in a specified reference \
    frame.',
    
    async function() {

        // taken from:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/gf.html
        const kernelsToLoad = [
            'lsk/a_old_versions/naif0009.tls',
            'pck/a_old_versions/pck00008.tpc',
            'spk/planets/a_old_versions/de421.bsp',
        ];
    
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');   
    
        const {state, lt} = spice.spkcpo("mercury", spice.str2et("2023 DEC 30"), "J2000", "OBSERVER", "NONE", [1,1,1], "EARTH", "J2000");

        
        const expectedState = {
            "r": [-14176383.802773606,-103194288.6067884,-38149178.5006784],
            "v": [-15.3518171130,-25.7271579005,-9.4210154030],
        }
        const expectedLt = 370.0215379048799;

        const tolerance = 1e-6;
        expectAlmostEqual(state, expectedState, tolerance);
        expect(lt).to.be.closeTo(expectedLt, tolerance);
    });
});
