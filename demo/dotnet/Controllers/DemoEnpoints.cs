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
            var list = new List<Artist>();
            list.Add(new Artist { Id = "1", Name = "Davido", Genre = "Afro-Pop", Albums = "2", Counrty = "Nigeria" });
            list.Add(new Artist { Id = "2", Name = "AKA", Genre = "Hip-Hop", Albums = "4", Counrty = "South-Africa" });
            list.Add(new Artist { Id = "3", Name = "Seyi Shay", Genre = "R&B", Albums = "2", Counrty = "Nigeria" });
            list.Add(new Artist { Id = "4", Name = "Sauti Sol", Genre = "Soul", Albums = "3", Counrty = "Kenya" });
            list.Add(new Artist { Id = "5", Name = "Nataly Orlov", Genre = "Afro-Pop", Albums = "2", Counrty = "Nigeria" });
            list.Add(new Artist { Id = "6", Name = "Justing Biber", Genre = "Hip-Hop", Albums = "4", Counrty = "South-Africa" });
            list.Add(new Artist { Id = "7", Name = "Sergei Apelbaum", Genre = "R&B", Albums = "2", Counrty = "Nigeria" });
            list.Add(new Artist { Id = "8", Name = "Galina NoName", Genre = "Soul", Albums = "3", Counrty = "Kenya" });

            return Json(list);
        }
    }

}
