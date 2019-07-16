using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace mvcAndReact.Controllers
{
    [AllowAnonymous]       
    public class DemoEndpoints : Controller
    {
        [Route("api/getFailedResponse")]
        [HttpGet]
        public HttpResponseMessage GetFail()
        {
            //  var response = new HttpResponseMessage(HttpStatusCode.NotFound);
            //  response.Content = new StringContent("I am not found");
            //  return response;
            throw new Exception("error");
        }

        [Route("api/getSuccessResponse")]
        [HttpGet]
        public JsonResult GetSucess()
        {
            Thread.Sleep(5000);
            var list = new List<string>();
            list.Add("First");
            list.Add("Second");
            list.Add("Third");
            return Json(list);
        }
    }

}
