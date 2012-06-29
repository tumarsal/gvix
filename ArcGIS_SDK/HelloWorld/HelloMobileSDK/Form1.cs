using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
//using ESRI.ArcGIS.Mobile;
//using ESRI.ArcGIS.Mobile.MobileServices;
//using ESRI.ArcGIS.Mobile.MapActions;

namespace HelloMobileSDK
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    // application exit
    private void menuItemExit_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    // zoom In menu
    private void menuItemZoomIn_Click(object sender, EventArgs e)
    {
      // set current map action to zoomIn
      //map1.CurrentMapAction = zoomInMapAction1;
    }

    // zoom out menu
    private void menuItemZoomOut_Click(object sender, EventArgs e)
    {
      // set current map action to zoomout
      //map1.CurrentMapAction = zoomOutMapAction1;
    }

    // pan menu
    private void menuItemPan_Click(object sender, EventArgs e)
    {
      // set current map action to pan
      //map1.CurrentMapAction = panMapAction1;
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      try
      {
        // specify mapcache folder
        //mobileService1.CacheStoragePath = @"\My Documents\MapCache";

        // specify map service url, modify this url if use your own server
        //mobileService1.Url = @"http://yourserver.yourdomain.com/arcgis/services/yourmapservice/MapServer/MobileServer";

        // open map cache
        //mobileService1.Open(CacheOpenMode.OpenOrCreate);

      }catch (Exception ex)
      {
        //MessageBox.Show("Failed to open map cache from " + mobileService1.CacheStoragePath);
      }
    }

    // when map extent is changed, get data from server if need
    private void map1_ExtentChanged(object sender, EventArgs e)
    {
      //if (!mobileService1.IsOpen)
      //  return;

      try
      {
        // get data from server
        //mobileService1.GetDataAsync(map1, true, null);
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.ToString());
      }
    }

  }
}