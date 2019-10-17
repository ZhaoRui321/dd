#pragma once
class CRegistryHandler
{
public:
	CRegistryHandler(void){}
	/// <summary>
	/// This class manages access to the Windows Registry.
	/// The registry root key is handled by a LabConstructor property which is currently defaulted to
	/// <code>private readonly string REG_ROOT = @"Software\SRL\LCTR-MassInstrument"</code>
	/// This can be overriden using the LabConstructor UI on an instance of the component.
	/// Utilities are provided to create registry key/value pairs in sub-key folders relative to the registry root 
	/// and read those values back out.
	/// </summary>
	/*public class RegistryHandler: IRegistryHandler
	{
		[LctrProperty("RegRoot")]
		private readonly string REG_ROOT = @"Software\SRL\LCTR-MassInstrument";
		private RegistryKey regRoot;

		/// <summary>
		/// Constructor for RegistryHandler class
		/// </summary>
		public RegistryHandler()
		{
			regRoot = Registry.LocalMachine.CreateSubKey(REG_ROOT);
		}

		/// <summary>
		/// Return the registry value as an object from a input key and a sub-folder relative to
		/// the registry root.
		/// </summary>
		/// <param name="subKey">Sub-folder name, relative to registry root</param>
		/// <param name="valueName">key name, assumed present in the sub-folder</param>
		/// <returns>value of key/value pair as object, otherwise null if not existing</returns>
		public object GetValue(string subKey, string valueName)
		{
			RegistryKey rk = this.regRoot.CreateSubKey(subKey);
			return rk.GetValue(valueName);
		}

		/// <summary>
		/// Return the registry value as an object from a input key located at the registry root. (No sub-folder)
		/// </summary>
		/// <param name="valueName">key name, assumed present in the registry root</param>
		/// <returns>value of key/value pair as object, otherwise null if not existing</returns>
		public object GetValue(string valueName)
		{
			return regRoot.GetValue(valueName);
		}

		/// <summary>
		/// Sets the value on the key/value pair contained in the sub-folder relative to the registry root.
		/// </summary>
		/// <param name="subKey">Sub-folder name, relative to registry root</param>
		/// <param name="valueName">key name, assumed present in the sub-folder</param>
		/// <param name="valueToSet">value of key/value pair as an object</param>
		public void SetValue(string subKey, string valueName, object valueToSet)
		{
			RegistryKey rk = this.regRoot.CreateSubKey(subKey);
			rk.SetValue(valueName, valueToSet);
			rk.Close();
		}
	}*/
};

