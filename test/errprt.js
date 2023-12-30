const expect = require('chai').expect;
const { spice } = require('..');

describe('errprt', function() {
  it('should retrieve or set the list of error message items to be output when an error is detected.',
   function() {

    const initialValue = spice.errprt('GET');

    // from:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/errprt_c.html
    const listValues = [
        { "input"    : "SHORT, EXPLAIN",
          "expected" : "SHORT, EXPLAIN" },
        { "input"    : "SHORT, LONG",
          "expected" : "SHORT, LONG" },
        { "input"    : "ALL",
          "expected" : "SHORT, LONG, EXPLAIN, TRACEBACK" },
        { "input"    : "NONE",
          "expected" : "" },
        { "input"    : "ALL, NONE, ALL, SHORT, NONE",
          "expected" : "" },
    ];

    listValues.map( element => {
        // Ensure a consistent state before the test
        spice.errprt('SET', "NONE");

        // Set the value
        spice.errprt('SET', element.input);

        // Test SET/GET
        expect(spice.errprt('GET')).to.be.equal(element.expected); 
    });

    spice.errprt('SET', initialValue);
  });
});
