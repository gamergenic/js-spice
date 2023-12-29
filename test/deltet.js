const expect = require('chai').expect;
const { spice, getKernels } = require('..');

describe('deltet', function() {
    it('should return the value of Delta ET (ET-UTC) for an input epoch.',
    async function() {

        await getKernels('lsk/latest_leapseconds.tls', 'test/data/naif/generic_kernels');

        const epoch = 0;
        const eptype = 'UTC';
        
        const actual = spice.deltet(epoch, eptype);

        const expected = 64.1839272856747;
        const tolerance = 1e-4;
        expect(actual).to.be.closeTo(expected, tolerance);
    });
});
