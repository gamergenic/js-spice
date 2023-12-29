const expect = require('chai').expect;
const { spice } = require('..');
const getKernels = require('./utility/getKernels');

const kernelsToLoad = [
    'lsk/latest_leapseconds.tls',
];
getKernels(kernelsToLoad);

describe('deltet', function() {
  it('should return the value of Delta ET (ET-UTC) for an input epoch.',
   function() {

    const epoch = 0;
    const eptype = 'UTC';
    
    const actual = spice.deltet(epoch, eptype);

    const expected = 64.1839272856747;
    const tolerance = 1e-4;
    expect(actual).to.be.closeTo(expected, tolerance);
  });
});
