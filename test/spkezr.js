const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('spkezr', function() {

    // Allow extra time as this is a computationally expensive operation.
    // Plus, we may need to download a number of kernels to run the test.
    this.timeout(60000);

    it('should return the state (position and velocity) of a target body \
relative to an observing body.',
    
    async function() {

        const kernelsToLoad = [
            'lsk/a_old_versions/naif0009.tls',
            'pck/a_old_versions/pck00008.tpc',
            'spk/planets/a_old_versions/de421.bsp',
        ];
    
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');   
    
        const {state, lt} = spice.spkezr('moon', spice.str2et("2023 DEC 30"), 'J2000', 'NONE', 'earth');

        const expectedState = {
            "r": [-266064.378455214,260865.49113570325,148871.48780060292],
            "v": [-0.7531372682257771,-0.5657889046714998,-0.2755241430154923],
        }
        const expectedLt = 1.3384351400997612;

        const tolerance = 1e-6;
        expectAlmostEqual(state, expectedState, tolerance);
        expect(lt).to.be.closeTo(expectedLt, tolerance);
    });
});
