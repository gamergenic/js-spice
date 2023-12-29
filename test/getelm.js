const expect = require('chai').expect;
const { spice, getKernels } = require('..');

describe('getelm', function() {
    it('should evaluate NORAD two-line element data for earth orbiting spacecraft.',
    
    async function() {
        // From:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/evsgp4_c.html
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/getelm_c.html

        await getKernels('lsk/naif0012.tls', 'test/data/naif/generic_kernels');

        const tle = [ '1 43908U 18111AJ  20146.60805006  .00000806  00000-0  34965-4 0  9999',
                      '2 43908  97.2676  47.2136 0020001 220.6050 139.3698 15.24999521 78544' ];

        const {elems} = spice.getelm(1957, tle);

        const expected = {
            "ndt20": 2.4422489185892878e-11,
            "ndd60": 0,
            "bstar": 0.000034965,
            "incl":  1.6976398755128366,
            "node0": 0.8240327717195948,
            "ecc":   0.0020001,
            "omega": 3.8502835963620905,
            "m0":    2.432461887845993,
            "n0":    0.06654065683196603,
            "epoch": 643689404.7102276
        };

        expect(elems).to.deep.equal(expected);
    });
});
