const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('spkpos', function() {

    // Allow extra time as this is a computationally expensive operation.
    // Plus, we may need to download a number of kernels to run the test.
    this.timeout(60000);

    it('Return the position of a target body relative to an observing body.',
    
    async function() {

        const kernelsToLoad = [
            'lsk/a_old_versions/naif0009.tls',
            'pck/a_old_versions/pck00008.tpc',
            'spk/planets/a_old_versions/de421.bsp',
        ];
    
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');   
    
        const {pos, lt} = spice.spkpos('moon', spice.str2et("2023 DEC 30"), 'J2000', 'NONE', 'earth');
        
        const expectedPosition = [-266064.378455214,260865.49113570325,148871.48780060292];
        const expectedLt = 1.3384351400997612;

        const tolerance = 1e-6;
        expectAlmostEqual(pos, expectedPosition, tolerance);
        expect(lt).to.be.closeTo(expectedLt, tolerance);
    });
});
