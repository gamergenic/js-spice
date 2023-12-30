const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('reclat', function() {
  it('should convert from rectangular coordinates to latitudinal coordinates.',
   function() {

    const rec = [-55658.44323296, -379226.32931475, -126505.93063865];
    const actual = spice.reclat(rec);

    const pi = 3.1415926536;
    const rpd = pi / 180;
    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/latrec_c.html
    const expected = {"radius": 403626.33912495, "lon":-98.34959789*rpd, "lat":-18.26566077*rpd};
    
    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
