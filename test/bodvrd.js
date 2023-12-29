const expect = require('chai').expect;
const { spice, getKernels } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

// kernel data required for testing bodvrd
const kernelsToLoad = [
    'pck/a_old_versions/pck00008.tpc',
];

describe('bodvrd', function() {
    it('should fetch from the kernel pool the double precision values \
of an item associated with a body (EARTH RADII).',
        async function() {

        // taken from:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');

        const actual = spice.bodvrd("EARTH", "RADII");

        const expected = [6378.140, 6378.140, 6356.750];
        const tolerance = 1e-2;
        expectAlmostEqual(actual, expected, tolerance); 
    });

    it('should return an array if results are multi-dimensional.', function() {

        // taken from:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html

        const actual = spice.bodvrd("399", "RADII");

        const expected = [6378.140, 6378.140, 6356.750];
        const tolerance = 1e-2;
        expectAlmostEqual(actual, expected, tolerance); 
    });
    
    it('should return a numeric value if results are 1-dimensional.', function() {

        // taken from:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html

        const actual = spice.bodvrd("EARTH", "LONG_AXIS");

        const expected = 0;
        expect(actual).to.be.equal(expected);
    });

    it('should throw an error if the kernel variable is not found.', 
        async function(){
 
        function test(){
            spice.bodvrd("EARTHLY", "INTELLIGENCE");
        }

        // Expect after the clear we can't read earth's radii
        expect(test).to.throw();
    });    
});
