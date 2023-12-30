const expect = require('chai').expect;
const { spice } = require('..');
const expectAlmostEqual = require('./utility/expectAlmostEqual');

describe('latrec', function() {
  it('should convert from latitudinal coordinates to rectangular coordinates.',
   function() {

    const pi = 3.1415926536;
    const rpd = pi / 180;
    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/latrec_c.html
    const lat = {"radius": 403626.33912495, "lon":-98.34959789*rpd, "lat":-18.26566077*rpd};
    
    const actual = spice.latrec(lat);

    const expected = [-55658.44323296, -379226.32931475, -126505.93063865];
    const tolerance = 1e-4;
    expectAlmostEqual(actual, expected, tolerance); 
  });
});
