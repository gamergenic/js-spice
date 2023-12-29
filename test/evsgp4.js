const expect = require('chai').expect;
const { spice, getGeophysicalConstants, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('evsgp4', function() {
    it('should evaluate NORAD two-line element data for earth orbiting spacecraft.',
    
    async function() {
        // From:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/evsgp4_c.html
        const geophs = await getGeophysicalConstants(true, 'pck/geophysical.ker', 'test/data/naif/generic_kernels');
        await getKernels('lsk/naif0012.tls', 'test/data/naif/generic_kernels');

        const et  = spice.str2et('2020-05-26 02:25:00');
        const tle = [ '1 43908U 18111AJ  20146.60805006  .00000806  00000-0  34965-4 0  9999',
                      '2 43908  97.2676  47.2136 0020001 220.6050 139.3698 15.24999521 78544' ];

        const {elems} = spice.getelm(1957, tle);

        const actual = spice.evsgp4(et, geophs, elems);

        const expected = {
            "r": [-4644.60403398, -5038.95025539, -337.27141116],
            "v": [   -0.45719025,     0.92884817,   -7.55917355]
        };
        const tolerance = 1e-8;

        expectAlmostEqual(actual, expected, tolerance);
    });
});
